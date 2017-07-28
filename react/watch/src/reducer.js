import { combineReducers } from 'redux';

import { reducer as watchReducer } from './watch';

const reducer = combineReducers({
  watch: watchReducer,
});

export default reducer;
