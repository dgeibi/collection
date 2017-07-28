import now from 'performance-now';
import TYPES from './constants';

export default (id) => {
  const stop = () => (dispatch, getState) => {
    const state = getState().watch[id];
    clearTimeout(state.timer);
    dispatch({
      id,
      type: TYPES.STOP,
    });
  };

  const tick = timer => (dispatch, getState) => {
    const state = getState().watch[id];
    const lastTime = state.time;
    const time = now();
    const diff = time - lastTime;
    const timeout = lastTime ? state.timeout - diff : state.timeout;

    dispatch({
      type: TYPES.TICK,
      time,
      id,
      timer,
      timeout,
    });
    if (timeout <= 0) dispatch(stop());
  };

  const init = (left, time) => ({
    type: TYPES.INIT,
    id,
    timeout: left,
    total: time,
  });

  const start = () => (dispatch, getState) => {
    const state = getState().watch[id];
    if (state.running) return;
    dispatch({
      type: TYPES.START,
      id,
    });
    const update = () => {
      const { timeout } = getState().watch[id];
      if (timeout > 0) {
        const timer = setTimeout(update, 50);
        dispatch(tick(timer));
      } else {
        dispatch(tick());
      }
    };
    update();
  };

  const reset = () => ({
    id,
    type: TYPES.RESET,
  });

  const pause = () => (dispatch, getState) => {
    const state = getState().watch[id];
    if (!state.running) return;
    clearTimeout(state.timer);
    dispatch(tick());
    dispatch({
      id,
      type: TYPES.PAUSE,
    });
  };

  return { start, stop, pause, reset, init, tick };
};
