### > Code Splitting
- tree shaking: elemination of dead (unused) code.
- bundling: the process of following imported files, getting used pieced of code (tree shaking), and merging them into a single file (bundle).
  - CRA, Next.js and similar tools provide webpack setup (module bundling) out of the box.
- code splitting: splitting the single bundle (can get very large) into multiple bundles that can be dynamically loaded (lazy loaded) at runtime based on what is currently needed by the user.

#### Dynamic Import
```js
  // before
  import { add } from './math';
  console.log(add(16, 26));

  // after
  import("./math").then(math => {
    console.log(math.add(16, 26));
  });
```

#### React.lazy & Suspense
```jsx
  // before
  import OtherComponent from './OtherComponent';
  
  // after 
  const OtherComponent = React.lazy(() => import('./OtherComponent')); 
  
  <MyErrorBoundary>
    <Suspense fallback={<div>Loading...</div>}>
      <OtherComponent />
    </Suspense>
  </MyErrorBoundary>
```
- `React.lazy()`: a function lets you render a dynamic import as a regular component.
  - it only supports `default exports`: `./OtherComponent` is a module with a default export containing a React component.
  - for named exports, we can create an intermediate module that reexports it as the default.
  - it should be inside a `Suspense` component
- `Suspense`: a component that allows us to use a fallback to indicate loading of the lazy components.
  - it can be placed anywhere above the lazy component(s).
  - the `fallback` prop accepts any React element.
- `ErrorBoundary`: catches errors triggered by lazy components (ex: failed to load due to network error)
  - it can be placed anywhere above the lazy component(s).
- a good place to start is with routes (pages). it will split bundles evenly, and will not disrupt user experience.


### > Error Boundaries
```jsx
  class ErrorBoundary extends React.Component {
    constructor(props) {
      super(props);
      this.state = { hasError: false };
    }

    static getDerivedStateFromError(error) {
      // update state to render the fallback UI.
      return { hasError: true };
    }

    componentDidCatch(error, errorInfo) {
      // log the error to an error reporting service 
      // (to learn about unhandled exceptions as they happen in production, and fix them)
      logErrorToMyService(error, errorInfo);
      // component stack traces can be found in errorInfo.componentStack
    }

    render() {
      if (this.state.hasError) {
        // render any custom fallback UI
        return <h1>Something went wrong.</h1>;
      }
      return this.props.children; 
    }
  }

  // usage
  <ErrorBoundary>
    <SomeComponent/>
  </ErrorBoundary>
```
- a React component that catches JS errors in child component tree, log errors, and display a fallback UI.
  - it is like JS catch {} block, but for components.
- it catches errors during rendering, in lifecycle methods, and in constructors.
- it doesn't catch:
  - errors within itself.
    - if it fails rendering the error message (fallback UI), the error will propagate to the closest error boundary above it.
    - use a parent error boundary to catch it.
  - errors for event handlers.
    - use `try / catch` statements to catch them.
  - errors of asynchronous code.
  - SSR errors.
- a class component is an error boundary if it implements `static getDerivedStateFromError()` and/or `componentDidCatch()` lifecycle methods.
- where to place error boundaries?
  - we may wrap top-level route components to display a “Something went wrong” message to the user.
  - we may also wrap individual widgets in an error boundary to protect them from crashing the rest of UI.
- as of React 16, errors that were not caught by any error boundary will result in unmounting of the whole React component tree.


### > Forwarding Refs
```jsx
  const FancyButton = React.forwardRef((props, ref) => (
    <button ref={ref} className="FancyButton">
      {props.children}
    </button>
  ));

  // You can now get a ref directly to the DOM button:
  const ref = React.createRef();
  <FancyButton ref={ref}>Click me!</FancyButton>;
```
- a technique for automatically passing a ref through a component to one of its children.
- we use it since the `ref` attribute is not available in the props (like `key`).
- useful for components that contain DOM elements that need to be accessed through the ref (button, input, etc).
- if you name the render function, DevTools will also include its name:
  - `React.forwardRef((props, ref) => ())`: name = ForwardRef
  - `React.forwardRef(function myFunction(props, ref)())`: name = ForwardRef(myFunction)
- see the docs for forwarding refs in HOCs.
