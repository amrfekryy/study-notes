### What?
JWT is a mechanism for authorization that replaces the old server session.

### Sessoin flow
- client: send a request with user credentials
- server: authenticate user based on credentials
    - create a session in memory and store user data (id, name, etc)
    - send session id as cookie to client
- client: send session id cookie with each request
- server:
    - get user from memory based on session id
    - check if user is authorized to the resource and send response

### JWT flow
- client: send a request with user credentials
- server: authenticate user based on credentials
  - create a JWT: encode user data and sign it with server's secret key
  - send token wich holds encoded user data to client
- client: send token with each request
- server:
  - verify signature on token and decrypt it to get user data 
  - check if user is authorized to the resource and send response

### Session VS JWT
- session: user info is stored on the server
  - server needs to lookup session id upon every request.
- JWT: user info is stored in the token on the client
  - server doesn't need to remember anything
  - we can use same token across multiple servers.

### How it Works
- check [jwt.io](https://jwt.io/) and this [video](https://www.youtube.com/watch?v=7Q17ubqLfaM&t=304s)
```js
  
  // creating a JWT
  const header = base64UrlEncode({
      "alg": "HS256", // algorithm
      "typ": "JWT" // token type
  })
  const payload = base64UrlEncode({
    "sub": "1234567890", // or user id
    "name": "John Doe", // additional data
    "iat": 1516239022, // issued at
    "exp": '' // expires at (optional)
  })

  // encrypt `${header}.${payload}` using secret key
  const signature = HMACSHA256(`${header}.${payload}`, 'your-secret-key')

  // send to client:
  const token = `${header}.${payload}.${signature}`

  const token = `eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c`
    
  // verify a JWT: header and payload are not changed by client
  const [header, payload, signature] = token.split('.')

  if (signature == HMACSHA256(`${header}.${payload}`, 'your-secret-key')) {
    /* valid token */
  } else { 
    /* invalid token */ 
  }
```