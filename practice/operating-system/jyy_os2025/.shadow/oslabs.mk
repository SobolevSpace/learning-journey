export TOKEN := ???

# ---------- DO NOT MODIFY ----------
# 本地开发：已关闭「每次 make 自动 git 追踪」和「在线 submit」。
# 若要向课程服务器提交，请恢复下面标注的段落。

export COURSE := OS2025
URL := 'https://jyywiki.cn/submit.sh'

ifeq ($(NAME),)
$(error Should make in each lab's directory)
endif

SRCS   += $(shell find . -maxdepth 1 -name "*.c")
DEPS   += $(shell find . -maxdepth 1 -name "*.h") $(SRCS) ../testkit/testkit.h ../testkit/testkit.c
CFLAGS  += -O2 -std=gnu2x -ggdb -Wall -I../testkit
LDFLAGS += 


.PHONY: all git-trace test clean submit commit-and-make

# 课程默认：commit-and-make（先 git-trace 再编译）。本地改为只编译：
.DEFAULT_GOAL := all
# .DEFAULT_GOAL := commit-and-make

# 课程原版：commit-and-make: git-trace all（恢复 git-trace 后改回这一行）
commit-and-make: all

$(NAME): $(DEPS)
	$(CC) $(CFLAGS) $(SRCS) ../testkit/testkit.c -o $@ $(LDFLAGS)

lib$(NAME).so: $(DEPS)
	$(CC) -fPIC -shared $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

clean:
	rm -f lib$(NAME).so $(NAME) $(NAME).so $(NAME)_test

# --- git-trace：同步 ../.shadow 并以 tracer 身份 commit（本地一般不需要）---
git-trace:
	@:
# 恢复课程行为时：删掉上面的 `@:`，取消下面注释。
# 	@find ../.shadow/ -maxdepth 1 -type d -name '[a-z]*' | xargs rm -rf
# 	@cp -r `find .. -maxdepth 1 -type d -name '[a-z]*'` ../.shadow/
# 	@git add ../.shadow -A --ignore-errors
# 	@while (test -e .git/index.lock); do sleep 0.1; done
# 	@(uname -a; uptime) | git commit -F - -q --author='tracer-nju <tracer@nju.edu.cn>' --no-verify --allow-empty
# 	@sync

# --- submit：拉取 jyywiki 提交脚本（本地不需要）---
submit:
	@echo "submit disabled for local dev; uncomment recipe in oslabs.mk to restore."
# 	@cd $(dir $(abspath $(lastword $(MAKEFILE_LIST)))) && \
# 	  curl -sSLf '$(URL)' > /dev/null && \
# 	  curl -sSLf '$(URL)' | bash
