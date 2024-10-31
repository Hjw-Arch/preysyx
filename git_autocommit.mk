# git_autocommit.mk

# 自动执行 Git 操作的默认消息
GIT_COMMIT_MSG ?= "Auto commit by Makefile"

# 定义前置操作
.PHONY: pre_git
pre_git:
	@git add .
	@git commit -m "$(GIT_COMMIT_MSG)"
	@git push

# 当任何目标被执行时，首先调用 pre_git
# 使用 MAKECMDGOALS 遍历所有目标
$(MAKECMDGOALS): pre_git
