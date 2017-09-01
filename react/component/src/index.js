import React from 'react'
import { render } from 'react-dom'
import SearchSelect from './components/SearchSelect'

function App() {
  return (
    <div>
      <div className='wrapper'>
        <section>
          <SearchSelect items={['a', 'b', 'c']} />
        </section>
      </div>
      <style jsx>
        {`
          .wrapper {
            max-width: 800px;
            margin: 0 auto;
          }
        `}
      </style>
    </div>
  )
}

render(<App />, document.getElementById('root'))
