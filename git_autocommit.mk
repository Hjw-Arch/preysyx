# git_autocommit.mk

# 自动执行 Git 操作的默认消息
GIT_COMMIT_MSG ?= Auto commit by Makefile

ROOT_DIR := ~/preysyx

# 定义前置操作
pre_git:
	@cd $(ROOT_DIR) && git add .
	@if [ -n "$$(git diff --cached)" ]; then \
		echo "Committing changes..."; \
		cd $(ROOT_DIR) && git commit -m "$(GIT_COMMIT_MSG)"; \
		cd $(ROOT_DIR) && git push; \
	else \
		echo "No changes to commit."; \
	fi
	@cd $(CURDIR) # 确保回到初始目录

# 当任何目标被执行时，首先调用 pre_git
# 使用 MAKECMDGOALS 遍历所有目标
$(MAKECMDGOALS) += pre_git
