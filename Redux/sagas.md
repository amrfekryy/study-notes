
```js
  const delay = (ms) => new Promise(res => setTimeout(res, ms))

	export function* taskSaga() {
		const action = {type: 'INCREMENT'}

		yield delay(1000) // delay(1000) = Promise
		yield call(delay, 1000) // call(delay, 1000) = { CALL: {fn: delay, args: [1000]}} "call a function"
		yield put(action) // put(action) = { PUT: {type: 'INCREMENT'} } "dispatch an action"

		const products = yield call(API.fetch, '/products') /*
			- call(API.fetch, '/products') evaluates to an effect { CALL: {fn: API.fetch, args: ['/products']}}
			- middleware suspends saga and executes the effect
			- middleware gives the result (products) back to the generator
		*/ 
	}

	export function* watcherSaga() {
		yield takeEvery(actionType, taskSaga)
	}

	export default function* rootSaga() {
		yield all([
			watcherSaga(), ...
		])
	}

	const sagaMiddleware = createSagaMiddleware()
	const store = ...
	sagaMiddleware.run(rootSaga)
```
- sagas are implemented using generator functions.
- saga yields effects
- effects are plain JS objects which contain instructions to be fulfilled by the middleware
- effect creators: `call`, `put`, ..
- when a middleware retrieves an effect yielded by a saga, the saga is paused until the effect is fulfilled.
- if the result of executing the effect by the middleware is a promise, saga is suspended until the promise resolves like in `delay(ms) / call(delay, ms)`.

- separation between effect creation and effect execution makes it possible to test our generator.
- we test effects instead of results of executing the effects.
- since effect creators return plain objects, we can reuse them in the test code.
	- this way we can comapre objects instead of the result of execution that might be a promise.

### Effect Creators
- `put(action)`: dispatch an action to the store.
- `call(fn, ...args)`: call the function with given arguments.
- `call([obj, obj.method], ...args)` as if we did obj.method(arg1, arg2 ...)
- `apply(obj, obj.method, [...args])` alias for the method invocation form
- `cps(fn, ...args, (error, result) => ())`. cps for Continuation Passing Style.

### Watchers
- `takeEvery(actionType, task)`: starts a task on every dispatch of actionType. allows multiple instances of task to be started concurrently.
- `takeLatest(actionType, task)`: runs task on latest dispatch of actionType. and cancels previously called instances of task.

### Error Handling
- we can catch errors inside the saga using `try/catch`
- see docs to know how to test errors.

### Channels
- `take` and `put` effects are used to communicate with the Redux store.
- channels generalize them to communicate with external event sources.
- or to communicate between sagas.
- or to queue specific actions from the store.


