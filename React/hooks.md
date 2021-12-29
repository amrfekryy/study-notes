### What?
Functions that let you “hook into” React features (ex: state, lifecycle) from function components (previously known as “stateless components”).

### Why?
- reusing stateful logic:
  - we can extract stateful logic with `custom hooks` instead of using advanced patterns (HOC, render props) which changes component hirarchy and make code less readable.
- replacing complexity of lifecycle methods:
  - `useEffect` hook groups related logic (separates concerns) in units rather than forcing a split based on lifecycle methods.
- solving class-components issues:
  - avoiding `this` keyword confusion, and having to bind event handlers.
  - optimization issues: classes don't minify well and make hot reloading unreliable.

### Rules
- only call hooks at top level
- only call hooks from React function components or custom hooks

### useState
```js
  const [value, setValue] = useState(initialValue);
```
- pass a function to the setter when you have to update based on the previous state.
- the setter replaces the old state.
  - in classes, the state is always and object, the setter auto merges updates.
  - use the spread operator to merge updates to first level of objects or append to arrays.
  - use a deepMerge function to merge updates to further levels of objects.

### useEffect
```js
  useEffect(() => { // effect function

    // (subscribe, fetch data, manipulate DOM, ..)
    
    return () => {} // clean up function (unsubscribe, ..)

  }, [/* dependency array (DA) */]);
```
- when the effect is run?
  - no DA: after every render
  - DA=[]: after first render only
  - DA=[...dependencies]: when a dependency updates
- cleanup function runs before excuting the next effect and before the component unmounts.

### useCallback
```js 
React.memo() 
// HOC that prevents a child component from rerendering upon parent rerender 
// child only rerenders if its props or state change
```
```js
  const callback1 = () => {/*  */}
  const callback2 = useCallback(() => {/*  */}, [/* dependency array */]) 
```
- `callback1` will have a new reference with every componenet rerender.
- `callback2` will have a new reference only when a dependency updates.
- when?
  1- when it is used in the dependencies list and checked for referential equlaity.
  2- when it is passed to optimized components (that use `React.memo`) that rely on referential equlaity to prevent unnecessary rerenders.

### useMemo
```js
  const callback = () => {/*  */}
  const value1 = callback()

  const value2 = useMemo(() => {/*  */; return value;}, [/* dependency array */]) 
```
- `value1` will be computed with every componenet rerender.
- `value2` will be computed only when a dependency updates.
- `useMemo` caches the return value of the callback, `useCallback` caches the callback instance itself.
- when? 
  - when the value is non premitive and is used in the dependencies list and checked for referential equlaity. 
  - when the value is computationally expensive to calculate.

### useRef
```jsx
  // usage 1: accessing DOM nodes:

  const inputRef = useRef(null);
  const useEffect(() => {
    inputRef.current.focus()
  }, [])
  return <input ref={inputRef} type="text" />
```
```jsx
  // usage 2: storing any mutable value similar to instance variables in a class component
  
  const [timer, setTimer] = useState(0)
  
  const intervalRef = useRef()

  useEffect(() => {
    intervalRef.current = setInterval(() => {
      setTimer(timer => timer + 1)
    }, 1000)
    return () => clearInterval(intervalRef.current)
  }, [])

  return <div>
    Timer: {timer}
    <button onClick={() => clearInterval(intervalRef.current)}>Clear Timer</button>
  </div>
```
- the value in `.current` will persist through rerenders, and it will not cause a rerender when its changed.

### useContext
```js  
  // 1- create context
  export const ContextName = React.createContext(initialValue)

  // 2- provide context by wrapping a parent component
  <ContextName.Provider value={/* the value to be passed */}>
    <ParentComponent/>
  </ContextName.Provider>
  
  // 3- consume context in a child component
  const value = useContext(ContextName)
```
- context provides a way to pass data through the components tree without having to pass props down manually at every level (prop drilling).
