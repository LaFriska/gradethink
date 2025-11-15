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
Assignment 1, 25%, 0.87
Assignment 2, 0.20, NA
Quiz 1, 0.05, 28/30
Final Exam, 0.50, NA 
```

### Displaying Courses

gradethink will be able to display courses statuses using a pretty-print layout. This can be done through `gradethink status <name>`. Several derived attributes will also be displayed. These may include a current weighted average, and also the weighted average needed in the `NA` components to achieve various grade bands (pass, credit, distinction, high distinction etc). It is possible that a verbose mode will be added to display these additional information, by adding the `-v` flag. 

### Hypothetical Grades

Grades can be set without mutating the course configuration file. This can be done via `gradethink tempset <course_name> <attr_name> <mark>`.