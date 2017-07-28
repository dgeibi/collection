import React, { Component } from 'react';
import { bindActionCreators } from 'redux';
import { connect } from 'react-redux';

import Btn from '../components/Btn';
import getActions from './get-actions';

function convertMS(ms) {
  if (ms < 0) return 0;
  const s = ms / 1e3;
  let sec = Math.ceil(s % 60);
  let min = Math.floor(s / 60);
  if (sec === 60) {
    min += 1;
    sec = 0;
  }

  min = min.toString().padStart(2, '0');
  sec = sec.toString().padStart(2, '0');

  return `${min}:${sec}`;
}

class Watch extends Component {
  componentWillMount() {
    this.props.actions.init(this.props.timeout, this.props.total);
  }

  render() {
    const { timeout, running, end } = this.props;
    const { pause, stop, start, reset } = this.props.actions;
    return (
      <div>
        <section>{convertMS(timeout)}</section>
        <section>
          <Btn show={!running && !end} onClick={start}>Start</Btn>
          <Btn show={running} onClick={pause}>Pause</Btn>
          <Btn show={running} onClick={stop}>Stop</Btn>
          <Btn show={end} onClick={reset}>Reset</Btn>
        </section>
      </div>
    );
  }
}

function mapDispatchToPropsFactory(dispatch, ownprops) {
  const id = ownprops.id;
  const actions = getActions(id);
  return ({
    actions: bindActionCreators(actions, dispatch),
  });
}

function mapStateToPropsFactory(state, ownprops) {
  const id = ownprops.id;
  return { ...state.watch[id] };
}

export default connect(
  mapStateToPropsFactory,
  mapDispatchToPropsFactory,
)(Watch);
