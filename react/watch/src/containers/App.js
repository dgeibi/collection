import React from 'react';
import { view as Watch } from '../watch';

function App() {
  return (
    <div>
      <Watch timeout={20} id={1} />
      <Watch timeout={30} id={2} />
    </div>
  );
}

export default App;
