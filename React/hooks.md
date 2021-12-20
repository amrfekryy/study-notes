### What?
Functions that let you “hook into” React features (ex: state, lifecycle) from function components (previously known as “stateless components”).

### Why?
- avoid `this` keyword confusion
  - in classes, we need to use `this` keyword, and remember to bind event handlers.
- optimization
  - classes don't minify well and make hot reloading unreliable.
- sharing stateful logic
  - in classes, we had to use advanced patterns (HOC, render props) which changes component hirarchy and make code less readable.
- group related logic into isolated units 
  - in classes, we are forced to split logic based on lifecycle methods.

### Rules
- only call inside a functional component or a custom hook
- only call hooks at top level

### useState
```js
  const [value, setValue] = useState(initialValue);
```
- pass a function to the setter when you have to update based on the previous state.
- the setter replaces the old state.
  - in classes, the state is always and object, the setter auto merges updates.
  - use the spread operator to merge updates to first level of objects or append to arrays.
  - use a deepMerge function to to merge updates to further levels of objects.

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
