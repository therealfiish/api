

# HWMNGR API

This API lets you keep track of your assignments (and I guess everyone else's). 

Currently hosted on `https://krrishk.hackclub.app/`.

## How to Input Assignments

There are two ways to input assignments into the API:

### 1. Send a POST request

Send a POST request to the API in the following format:
```json
{
  "assignment": "x",
  "course": "y",
  "days_due": z
}
```
- `x` = assignment name
- `y` = course
- `z` = number of days remaining until the assignment is due

### 2. Send a GET request (Easier Method)

Send a GET request to this route:
```
/assignment/course/days_remaining
```
Replace `course` and `days_remaining` as needed. 
*IMPORTANT: Use `%20` instead of spaces!*

---

## How to Check Your Assignments

There are multiple ways to check your assignments:

1. **By due date**  
   Send a GET request to the route `/duenext`.

2. **By class name**  
   Send a GET request to the route `/byclass`.

---

Thanks for using the API!

--- 

hint: to see this in your terminal, send a GET request to the root.
