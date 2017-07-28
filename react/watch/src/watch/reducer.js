import TYPES from './constants';

export default function reducer(state = {}, action) {
  const currState = state[action.id];
  const { type, id, ...rest } = action;

  switch (type) {
    case TYPES.INIT:
      return {
        ...state,
        [id]: {
          running: false,
          total: (action.total || action.timeout) * 1e3,
          timeout: (action.timeout || action.total) * 1e3,
        },
      };
    case TYPES.TICK: {
      const end = action.timeout <= 0;
      return {
        ...state,
        [id]: {
          ...currState,
          ...rest,
          end,
        },
      };
    }
    case TYPES.START: {
      return {
        ...state,
        [id]: {
          ...state[id],
          running: true,
        },
      };
    }
    case TYPES.PAUSE: {
      return {
        ...state,
        [id]: {
          ...state[id],
          running: false,
          time: null,
        },
      };
    }
    case TYPES.RESET: {
      return {
        ...state,
        [id]: {
          ...state[id],
          timeout: state[id].total,
          end: state[id].total <= 0,
        },
      };
    }
    case TYPES.STOP: {
      return {
        ...state,
        [id]: {
          ...state[id],
          timeout: 0,
          time: null,
          running: false,
          end: true,
          timer: null,
        },
      };
    }
    default:
      return state;
  }
}
