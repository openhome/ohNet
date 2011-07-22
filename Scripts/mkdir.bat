@echo off
rem mkdir will complain if the directory already exists, so
rem we don't want to invoke it if the directory exists, but
rem we *do* want an error if a file of the same name exists
rem instead of a directory. We test for the existence of \*
rem in the directory because this will fail for a file but
rem succeed for a directory, even an empty one, because the
rem directory must contain "." and ".." as entries.
if not exist %1\* mkdir %1
