import React, { Component } from 'react'
import { Button } from 'antd'

import { connect } from 'redux-zero/react'
import shallowEqual from 'fbjs/lib/shallowEqual'

import JobScheduler from '../../FCFSJobScheduler'

class View extends Component {
  constructor(props, context) {
    super(props, context)
    this.state = {
      time: 0
    }
    if (props.opts) {
      this.loadScheduler(props.opts)
    } else {
      this.scheduler = null
    }
  }

  loadScheduler(opts) {
    this.scheduler = new JobScheduler(opts)
    this.scheduler.loadJob(0)
  }

  componentWillReceiveProps(nextProps) {
    if (nextProps.opts && !shallowEqual(nextProps.opts, this.props.opts)) {
      this.loadScheduler(nextProps.opts)
      if (this.state.time !== 0) {
        this.setState({
          time: 0
        })
      }
    }
  }

  tick = () => {
    const { scheduler } = this
    if (scheduler && !scheduler.isQueueEmpty()) {
      this.setState({
        time: scheduler.run(this.state.time)
      })
    }
  }

  render() {
    const { scheduler } = this
    const { time } = this.state
    if (!scheduler) return null
    if (scheduler.isQueueEmpty()) return <p>end {time}</p>
    return <p> {time} {scheduler.runningCnt}
      <Button onClick={this.tick}>Next Tick</Button>
    </p>
  }
}

export default connect(({ opts }) => ({ opts }))(View)
