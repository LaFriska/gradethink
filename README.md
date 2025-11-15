# gradethink

gradethink is a CLI app used to track assessment grades written in C. This will be particularly useful in estimating grades, or calculating assessment averages of various courses. 

## Software Specification 

### Overview

All operations using gradethink will be through the terminal by executing a `gradethink` program. This software should be compatible on unix-like operating systems. 

### Course

- A course can be added through `gradethink add <name>`. 
- A course can be deleted through `gradethink delete <name>`.
- Each course has several *components*. Components can be things like assignments, exams, or quizes. Each component has the following associated elements: a string `name`, a number `weight` between 0 and 1, `marks`, which represents the marks the student currently has out of `weight`, and `percentage`, which is `marks`/`weight` as a percentage. Optionally and by default, `marks` and `percentage` is set to a special value `NA` which means a student has not yet finished this component. 

All components of a given course are stored as line-separated and comma-separated attributes. This is placed in the `$HOME/.config/gradethink/<course_name>.txt` file. Courses can be configured by editting this file. Here is an example. 

**Name:** `COMP1234.txt`
**Contents:**
```
Assignment 1, 0.25, 0.87
Assignment 2, 0.25, NA
Final Exam, 0.50, NA 
```

### Displaying Courses

gradethink will be able to display courses statuses using a pretty-print layout. This can be done through `gradethink status <name>`.
