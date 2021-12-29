### What?
- JS library for managing "global" application state.

### Why?
- it makes it easier to understand when, where, why, and how the state in the application is being updated, and how application logic will behave when those changes occur.
- writing testable code.

### When?
- medium or large-sized codebase apps. with many contributors.
- large state to be managed.
- frequently updated state.
- complex logic to update state.

### Libraries and Tools
- React-Redux: integrating Redux and React.
- RTK: recommended way to write Redux logic.
- Redux DevTools Extension: time-travel debugging.

### Redux Parts
#### Action
- an action is a plain JS object that describes an event that happened in the application.
```js
	const action = {
		type: 'domain/eventName', // a string that describes what happend in the app
		payload: '', // optional - additional data (any type) needed to perform the changing action
	}
```

#### Reducer
- a reducer is an event listener which handles events based on the received action (event) type.
```js
	const initialState = {} // usually and object, can be array or primitive

	function reducer(state=initialState, action) {
		/* 
			perform conditional logic (if/else or switch/case or ..) that calcualates the new State based on action type and old state

			if doesn't care about action, return existing state unchanged. 
		*/
	}
```
- reducers should update the state immutably.
- they should be pure functions without side effects.

#### Store
- a container that holds the applications's glabal state. it is a JS object with special functions.
```js
	import { createStore } from 'redux'
	const store = createStore(rootReducer)
	// or with RTK
	import { configureStore } from '@reduxjs/toolkit'
	const store = configureStore({ reducer: counterReducer })

	store.dispatch(action) // the only way to update state is to dispatch an action (trigger an event)

	function render() {
		const selectValue = state => state.path.to.value

		const value = selectValue(store.getState())
		// update UI with new value
	}
	store.subscribe(render) // notify when state updates
```

#### Redux Concepts and Principles
- single source of truth (store): all data in one place.
	- easier to debug and inspect app's state.
	- centralizing logic that needs to interact with the entire application.
- state is read-only: only way to change the state is to dispatch an action.
	- UI won't accidentally overwrite data.
	- easier to trace why a state update happened.
- changes are made with pure reducer functions

### Data Flow
- initial setup:
	- define and create `actions` (events).
	- create `reducers` (event listeners).
	- create `store`: calls root reducer initially and saves return value as initial state.
	- UI access current state, subscribe to store updates.	
- updates:
	- something happens in the app, like user interactions.
	- code `dispatch` an action to the store to tell it what happend.
	- store runs the `reducer` function to calculate the new state based on the old state and the action.
	- store notifies `subscribers` to update UI with the new state.
