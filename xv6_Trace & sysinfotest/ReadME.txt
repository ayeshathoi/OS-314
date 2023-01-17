# Do the assignment
# run "make clean" 
# Unzip xv6-riscv-riscv.zip somewhere
# Open it
# Open terminal inside
git init
git add .
git commit -am "fresh_copy_on_branch_master"
git branch --create assignment1
git switch assignment1
# Back to the folder (Dont close terminal)
# Delete everything except .git 
# Copy everything from assignment to here
# Back to the terminal
git add .
git commit -am "assigment_done_on_branch_assignment1"
git diff HEAD > 1805062.patch
