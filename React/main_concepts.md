### JSX
- JS syntax extension: lets you write html-like syntax in JS.
- syntacitc suger for the expression `React.creatElemet(component, props, ...children)`.
	- component can be string, a subclass of React.Component, or a plain function.
	- evaluates to React element (JS object).
- why? React separate concerns based on `components` instead of `technologies`.
- JS expression can be embedded in JSX using `{}`

### Rendering Elements
- `ReactDOM.render(element, document.getElementById('root'))`
- React DOM (VirtualDOM) compares the element and its children to the previous one, and only updates the RealDOM where necessary.

### Components
- let you split the UI into independent, reusable pieces, and think about each piece in isolation.
- can be a function or a class. each has additional features. 
- a compoennt accepts a single props object and returns a React element.
- a component can be composed of other components.
- a part of a component should be extracted into its own component when its reused or if it is complex enough.
- props are read-only: a components must act like a pure functions with respect to its props.

### State and Lifecycle
- state is similar to props, but it is private and fully controlled by the component.
- only a single instance of a class component is used through rerenders, which allow for other features like local state and life cycle methods.
- to use local state in a class component, we need to initialize it inside a constructor.
	- if a constructor is used, we should call the base constructor with props: `super(props)`.
- life cycle methods are special methods that are automatically called during the component life cycle phases:
	- mounting: `componentDidMount`
	- updation: `componentDidUpdate`
	- unmounting: `componentWillUnmount`
- we can add additional class fields using `this.fieldName` and access it anywhere in the class.
- use state properly:
	- don't modify state directly, use `this.setState()`
	- state updates may be asyncronous. 
		- don't rely on `this.state` and `this.props` values while updating
		- use `this.setState((state, props) => {})` instead.
	- state updates are merged (shallowly).
- React has `unidirectional data flow`:
	- all components are isolated.
	- a local state is owned by a specific comoponent.
	- data (state/props) can only be passed form parent to children.

### Handling Events
- React VS DOM, differences:
	- events are named using `camelCase`, rather than `lowercase`.
  - with JSX you pass a `function` as the event handler, rather than a `string`.
  - prevent default behaviour with `e.preventDefault()` rather than `return false`.
    - `e` is a cross-browser compatible [synthetic event](https://reactjs.org/docs/events.html)
  - we generally don't need to `addEventListener`.

- in a class component, we handle events with:
  - `class methods`: they have their own `this`. must bind them in constructor to so `this` refers to the class.
  - `class fields`: uses the arrow function syntax. enabled by default in CRA.
  - `inline arrow function`: but they are created with each render. will cause extra rerenders of lower components if passed in props.

- passing extra args to handler:
  ```jsx
    handleClick(id, e) {/*  */}

    // equivalent
    <button onClick={(e) => this.handleClick(id, e)}>click</button>
    <button onClick={this.handleClick.bind(this, id)}>click</button>
  ```

### Conditional Rendering
- create components to encapsulate different behaviours, and use `if` to render one of them conditionally.
- inline if with `&&` operator:
	- `expression && expression && expression ..`
	- evaluates to first falsy expression, or last expression if all are truthy.
	- we put JSX as the last expression to be rendered when previous conditions are true.
	- some falsy values are rendered like `0`, make sure to use `!!` before conditions to convert them to (true/false).
- inline if-else with conditional operator:
  - `condition ? expression : expression`
- return `null` instead of JSX to hide a component.
  - it doesn't affect the firing of the life cycle methods.

### Lists and Keys
- we need to provide a unique string `key` to list items (elements/components) to optimize performance.
- keys help React identify changes in a list and only update where necessary.
- the key is placed on elements/components inside the `map()` call.
- item's key has to be unique among its siblings. not globally.
- React defaults to using indexes as keys if not provided explicitly.
  - using indexes is discouraged if the order of the list changes. since the new order will cause switching keys between items.
- keys serves as a hint to React, but they are not passed as a prop to the component.

### Forms
- in React we use `state` to control the value of the form elements.
- we set `value` attribute on form inputs to display the value from state (-> controlled components).
- we use `onChnage` to get user input (`e.target.value`) and update the state, which will rerender and update the `value` attribute.
- with the inputs values in the state:
  - we can access them in the submit handler
  - we can pass them to other UI elements
  - we can reset them from other event handlers.

- React VS HTML:
  ```jsx
    // text input (similar)
    html = <input type="text" />
    react = <input type="text" />

    // textarea (different)
    html = <textarea>Text</textarea>
    react = <textarea value="Text"/>

    // select (different)
    html = <select>
      <option value='one' selected>one</option>
      <option value='two'>two</option>
    </select>
    react = <select value='one'>
      <option value='one'>one</option>
      <option value='two'>two</option>
    </select>
    // or react = <select multiple={true} value={['B', 'C']}></select>
  ```
  - React uses the value attribute in `<textarea>` and `<select>` so they can be implemented as controlled components.
  - the `<input type="file"/>` is uncontrolled in React as its value is read-only. [check here](https://reactjs.org/docs/uncontrolled-components.html#the-file-input-tag).

- handling multiple inputs:
  ```js
    // we can add a `name` attribute on the input elements and use one change handler.
    handleChange(event) {
      const target = event.target;
      const value = target.type === 'checkbox' ? target.checked : target.value;
      const name = target.name;

      this.setState({
        [name]: value
      });
    }
  ```
- check [uncontrolled coomponents](https://reactjs.org/docs/uncontrolled-components.html)

### Lifting State Up
- sharing one state between multiple components by moving it up to their closest common ancestor.
- we rely on the unidirectional data flow to sync the components.
- lifting state involves writing more “boilerplate” code than two-way binding approaches, but as a benefit, it takes less work to find and isolate bugs.
- if something can be derived from either props or state, it probably shouldn’t be in the state.

### Composition VS Inheritance
- React has a powerful composition model.
- container components:
  - useful for generic components like Sidebar or Dialog where we don’t know their children ahead of time.
  - when we wrap the component (use the closing tag) around any JSX. it gets passed as the special `children` prop.
  - we can have unlimited slots in a container by passing components directly in multiple props.

### Thinking in React
- create a mock design
- break the UI into a comoponent hierarchy.
  - draw boxes around (components/subcomponents) and give them names.
  - 