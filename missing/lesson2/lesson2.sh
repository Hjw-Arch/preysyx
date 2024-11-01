#! /bin/bash
ls -l -A --block-size=M --sort=time --color=auto

# marco.sh

# 定义 marco 函数
marco() {
    # 保存当前工作目录到环境变量 MARCO_DIR
    export MARCO_DIR=$(pwd)
    echo "Marco executed at: $MARCO_DIR"
}

# 定义 polo 函数
polo() {
    if [ -z "$MARCO_DIR" ]; then
        echo "Error: No directory saved with marco."
    else
        # 切换到保存的目录
        cd "$MARCO_DIR"
        echo "Polo returned to: $MARCO_DIR"
    fi
}
