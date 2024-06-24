Watch this [video](https://youtu.be/tRZGeaHPoaw)  

summery
----------
git config --global user.name "Athro"
git config --global user.email ayeshaathoi62@gmail.com
git config --global init.default branch main
git config -h
git help config
clear

git status ; -- kon branch e asi eita jana jabe

cd foldername
git init
git add sd.jpg ; to track a file
git rm --cached sd.jpg; to untrack again
--------------------------------
git add . or git add A or git add --all
--------------------------------
git commit -m "first commit - committing all files to the repository"

----------------------------------
git diff; to know the difference between modification
-----------------------------------
git add "changedFile"
-----------------------------------
git restore --staged changedFile; to restore to workingFile
-----------------------------------
workingFile -> Staging -> Commit
-----------------------------------
git rm filename
-----------------------------------
git restore filename
-----------------------------------
git mv "oldname" "newname"
-----------------------------------
git log
-----------------------------------
git log --oneline
-----------------------------------
git commit -m "change file name of Primary Logo.png" --amend ; recent tar change kore dibe
--------------------------
git log -p
---------------------------
git help log
---------------------------
git reset commitNumber // to restore
-------------------------------
git rebase -i --root
-------------------------------
git commit -a -m "updated something in this file"
--------------------------------

to ignore a file :
create .gitignore as a notepad
---------------------------------------
write in .gitignore file :
---------------------------------------
#ignore all .txt files
*.txt
----------------------------------------

#Create new Branch

git branch newBranch
-----------------------
#See all the branches
git branch
-----------------------
#switch to a branch
git switch BranchName
-----------------------
git switch -c UpdateText
------------------------
git commit -a -m "message"
--------------------------
git switch MainbranchName
git merge -m "merge newBranch to main" NewBranch
----------------------------
git branch -d DeleteBranch



merge Conflict
-----------------------------
git switch -c NewBranch
update something
git commit -a -m "message"
git switch MasterBranch
update that samething
git commit -a -m "message"
git merge -m "merge newBranch to main" NewBranch
-------------------------------------------------
resolve:
1. open the file. difference will be shown in merge view. then you will choose. 
THEN COMMIT
-------------------------------------------------

How to add into github acc
------------------------------------------------
…or create a new repository on the command line
echo "# PracticeGitHub" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/ayeshathoi/PracticeGitHub.git
git push -u origin main
…or push an existing repository from the command line
git remote add origin https://github.com/ayeshathoi/PracticeGitHub.git
git branch -M main
git push -u origin main
------------------------------
git push --all ; to push all branch
------------------------------
to update from local to github
------------------------------
git fetch
git merge
or
git pull
