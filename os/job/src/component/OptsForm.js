import { Form, Row, Col, Input, Button, Icon } from 'antd'
import React, { Component } from 'react'
import { connect } from 'redux-zero/react'

import * as validators from '../utils/validators'
import pick from '../utils/pick'

const FormItem = Form.Item

let uuid = 0
class OptsForm extends Component {
  handleSubmit = e => {
    e.preventDefault()
    const { form, setOpts } = this.props
    form.validateFields({ force: true }, (err, values) => {
      if (err) {
        return
      }
      const opts = pick(
        values,
        ['degree', 'rrSlice', 'maxMemSize'],
        ({ data, key, value }) => {
          data[key] = Number(value) // eslint-disable-line
        }
      )
      const jobOptKeys = ['arriveTime', 'memSize', 'needTime']
      opts.jcbs = values.keys.map(i =>
        pick(values, jobOptKeys.map(x => `${x}-${i}`), ({ data, index, value }) => {
          data[jobOptKeys[index]] = Number(value) // eslint-disable-line
        })
      )
      setOpts(opts)
    })
  }

  handleReset = () => {
    this.props.form.resetFields()
  }

  remove = k => {
    const { form } = this.props
    const keys = form.getFieldValue('keys')
    if (keys.length === 1) {
      return
    }
    form.setFieldsValue({
      keys: keys.filter(key => key !== k),
    })
  }

  add = () => {
    const { form } = this.props
    const keys = form.getFieldValue('keys')
    uuid++
    const nextKeys = keys.concat(uuid)
    form.setFieldsValue({
      keys: nextKeys,
    })
  }

  validMemSize = (rule, value, callback) => {
    const x = Number(this.props.form.getFieldValue('maxMemSize'))
    const n = Number(value)
    if (Number.isNaN(x) || Number.isNaN(n) || n < x || (Number.isFinite(n) && n === x)) {
      return callback()
    }
    return callback('作业内存大小不能超过总内存大小')
  }

  getSchedulerFields() {
    const { getFieldDecorator } = this.props.form
    return [
      <Col span={8} key="degree">
        <FormItem label="度">
          {getFieldDecorator('degree', {
            validateTrigger: ['onChange'],
            rules: [
              {
                required: true,
                message: '请输入度',
              },
              {
                validator: validators.isPostiveInteger,
              },
            ],
          })(<Input />)}
        </FormItem>
      </Col>,
      <Col span={8} key="rrSlice">
        <FormItem label="进程调度时间片大小">
          {getFieldDecorator('rrSlice', {
            validateTrigger: ['onChange'],
            rules: [
              {
                required: true,
                message: '请输入时间片大小',
              },
              {
                validator: validators.isPostiveInteger,
              },
            ],
          })(<Input />)}
        </FormItem>
      </Col>,
      <Col span={8} key="maxMemSize">
        <FormItem label="内存总大小">
          {getFieldDecorator('maxMemSize', {
            validateTrigger: ['onChange'],
            rules: [
              {
                required: true,
                message: '请输入内存总大小',
              },
              {
                validator: validators.isPositiveNumber,
              },
            ],
          })(<Input />)}
        </FormItem>
      </Col>,
    ]
  }

  getJobItemFields() {
    const { getFieldDecorator, getFieldValue } = this.props.form
    getFieldDecorator('keys', { initialValue: [0] })
    const keys = getFieldValue('keys')
    const minusCircle = k => ({
      addonAfter:
        keys.length > 1 ? (
          <Icon
            type="minus-circle-o"
            disabled={keys.length === 1}
            onClick={() => this.remove(k)}
          />
        ) : null,
    })

    return keys.map(k => (
      <Row gutter={24} key={k}>
        <Col span={8}>
          <FormItem required={false}>
            {getFieldDecorator(`arriveTime-${k}`, {
              validateTrigger: ['onChange'],
              rules: [
                {
                  required: true,
                  message: '请输入作业到达时间',
                },
                {
                  validator: validators.isPostiveInteger,
                },
              ],
            })(<Input placeholder="作业到达时间" />)}
          </FormItem>
        </Col>
        <Col span={8}>
          <FormItem required={false}>
            {getFieldDecorator(`needTime-${k}`, {
              validateTrigger: ['onChange'],
              rules: [
                {
                  required: true,
                  message: '请输入作业需要的时间',
                },
                {
                  validator: validators.isPostiveInteger,
                },
              ],
            })(<Input placeholder="作业需要的时间" />)}
          </FormItem>
        </Col>

        <Col span={8}>
          <FormItem required={false}>
            {getFieldDecorator(`memSize-${k}`, {
              validateTrigger: ['onChange'],
              rules: [
                {
                  required: true,
                  message: '请输入作业内存大小',
                },
                {
                  validator: validators.isPositiveNumber,
                },
                {
                  validator: this.validMemSize,
                },
              ],
            })(<Input placeholder="作业内存大小" {...minusCircle(k)} />)}
          </FormItem>
        </Col>
      </Row>
    ))
  }

  render() {
    return (
      <Form onSubmit={this.handleSearch}>
        <Row gutter={24}>{this.getSchedulerFields()}</Row>
        {this.getJobItemFields()}
        <Row gutter={24}>
          <Col span={16}>
            <Button
              type="dashed"
              onClick={this.add}
              css={{
                width: '100%',
              }}
            >
              <Icon type="plus" /> 增加作业
            </Button>
          </Col>
          <Col span={8}>
            <Button type="primary" htmlType="submit" onClick={this.handleSubmit}>
              提交
            </Button>
            <Button css={{ marginLeft: 8 }} onClick={this.handleReset}>
              重置
            </Button>
          </Col>
        </Row>
      </Form>
    )
  }
}

export default connect(null, {
  setOpts(state, opts) {
    return { opts }
  },
})(Form.create()(OptsForm))
