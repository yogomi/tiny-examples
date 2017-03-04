import React from 'react';
import { render } from 'react-dom';

import Hello from './components/hello.jsx';
import World from './components/world.jsx';

render(
  <div>
    <Hello></Hello>
    <World></World>
  </div>,
  document.getElementById('app')
);
