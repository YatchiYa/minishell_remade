# minishell
## How to work together with github
### 1. Clone data from github
```
git clone [remote repository URL]
```
### 2. Create new branch for adding new code
```
git branch [branch_name]
git checkout [branch_name]
// if you want to do at once
git checkout -b [branch_name]
```
### 3. Commit and push to github
```
git add -A
git commit -m [commit_message]
git push -u origin [branch_name]
```
### 4. Ask pull request on github
### 5. Project manager check which code is changed and merge it on github
### 6. Syncronize between remote and local
```
git checkout master
git pull origin master
```

### Redirections and pipe resources
1. [https://putaindecode.io/articles/maitriser-les-redirections-shell/](https://putaindecode.io/articles/maitriser-les-redirections-shell/)
2. [http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html](http://www.cs.loyola.edu/~jglenn/702/S2005/Examples/dup2.html)
