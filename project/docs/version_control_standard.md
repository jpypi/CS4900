# Version Control Standard

## Version Control System
git

## Note About Commit Messages
Read this webpage on how to write conforming commit messages.
http://chris.beams.io/posts/git-commit/

## Example Workflow
This webpage gives an example of good git workflow.
https://sandofsky.com/blog/git-workflow.html

## Workflow Notes
- Master branch will be stable, working
- Feature branches can be merged into master only when feature is fully
  functioning
- When updating local copy of code repo, attempt to avoid merge bubbles by using
  rebase.
- Testing
    - Make sure unit tests exist for new code
    - Unit tests run, and pass before pushing to master
    - Code in progress can reside in non-master branches
