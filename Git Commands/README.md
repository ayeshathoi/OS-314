### Watch this [video](https://youtu.be/tRZGeaHPoaw)  

### summery
- git config --global user.name "Athro"
- git config --global user.email ayeshaathoi62@gmail.com
- git config --global init.default branch main
- git config -h
- git help config
- clear

---
### To know the current branch
git status
---
### Tracking & Untrack a file
- cd foldername
- git init
- git add sd.jpg (Tracking)
- git rm --cached filename.jpg (Untracking)
---
### Adding all element from a folder

- One way     : git add .
- Second way  : git add A 
- Third way   : git add --all
---
### Commit
- git commit -m "Msg"
---
### To know the difference between modification
- git diff

---

### To add the changed File
- git add "changedFile"

---

### To restore to workingFile 
- git restore --staged changedFile
- workingFile -> Staging -> Commit
---
### To remove a file
- git rm filename
---
### To restore a file 
- git restore filename
---
### To rename a file
- git mv "oldname" "newname"
---
### To see the log
- git log
---
### To see the log in one line
- git log --oneline
---
### To amend the recent log (msg)
- git commit -m "change file name of Primary Logo.png" --amend 
---
### Log related more commands
- git log -p
- git help log
- git reset commitNumber (To Restore)
- git rebase -i --root
- git commit -a -m "updated something in this file"
---
### To ignore a file :
- create .gitignore as a notepad
- write in .gitignore file :
    - #ignore all .txt files
    - *.txt

### Create new Branch
- git branch newBranch
---
### See all the branches
- git branch
---
### Switch to a branch
- git switch BranchName
---
### Create and switch to a branch
- git switch -c UpdateText
---
### To commit 
git commit -a -m "message"
---
### To merge a branch
- git switch MainbranchName
- git merge -m "merge newBranch to main" NewBranch
---
### To delete a branch
- git branch -d DeleteBranch

---

## Merge Conflict
- git switch -c NewBranch
- update something
- git commit -a -m "message"
- git switch MasterBranch
- update that samething
- git commit -a -m "message"
- git merge -m "merge newBranch to main" NewBranch

Solution : 
- open the file. difference will be shown in merge view. then you will choose. 
- THEN COMMIT

---

## How to add into github acc
--- 
### OneWay : 
- create a new repository on the command line
- echo"# PracticeGitHub" >> README.md
- git init
- git add README.md
- git commit -m "first commit"
- git branch -M main
- git remote add origin https://github.com/ayeshathoi/PracticeGitHub.git
- git push -u origin main

### Another Way : 
- push an existing repository from the command line
- git remote add origin https://github.com/ayeshathoi/PracticeGitHub.git
- git branch -M main
- git push -u origin main
--- 
### To push all branch
- git push --all 
---
### To update from local to github
- One Way : 
    - git fetch
    - git merge
- Another Way : git pull

