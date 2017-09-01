import React, { Component } from 'react'

const width = '200px'

class SearchSelect extends Component {
  constructor(props) {
    super(props)
    this.state = {
      value: '',
    }
  }

  onValueChange = (e) => {
    this.setValue(e.target.value)
  }

  onClick = (e) => {
    if (!e.target.matches('li')) return
    this.setValue(e.target.textContent)
  }

  setValue(value) {
    if (value !== this.state.value) this.setState({ value })
  }

  render() {
    const { value } = this.state
    const regex = new RegExp(String(value).replace(/\\/g, '\\\\'), 'i')
    return (
      <div>
        <div>
          <input type='search' value={value} onInput={this.onValueChange} />
          <ul onClick={this.onClick}>
            {this.props.items.map(item =>
              <li key={item} className={regex.test(item) ? '' : 'hide'}>
                {item}
              </li>
            )}
          </ul>
        </div>
        <style jsx>{`
          div {
            position: relative;
            max-width: ${width};
            box-sizing: border-box;
          }

          div > * {
            box-sizing: inherit;
          }

          div:hover ul,
          div input:focus + ul {
            visibility: visible;
          }

          input {
            width: 100%;
            outline: 0;
          }

          ul {
            z-index: 99;
            position: absolute;
            background: #fff;
            list-style: none;
            width: 100%;
            margin-top: 0;
            border: 1px solid #eee;
            border-top: 0;
            padding: 0;
            margin: 0;
            visibility: hidden;
            max-height: 150px;
            overflow-y: auto;
          }

          ul li {
            padding-left: 10px;
            line-height: 1.5;
          }

          ul li.hide {
            display: none;
          }

          ul li:hover {
            background: #eee;
          }
        `}</style>
      </div>
    )
  }
}

export default SearchSelect
