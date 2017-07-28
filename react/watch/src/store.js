import { createStore, applyMiddleware, compose } from 'redux';
import ThunkMiddleware from 'redux-thunk';

import rootReducer from './reducer';

const middlewares = [ThunkMiddleware];
const storeEnhancers = compose(
  applyMiddleware(...middlewares),
  (window && window.devToolsExtension) ? window.devToolsExtension() : f => f,
);

const store = createStore(rootReducer, {}, storeEnhancers);

export default store;
