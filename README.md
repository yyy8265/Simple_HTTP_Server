# Linux 常用命令总结

## 1. 文件和目录操作

| 命令              | 用法示例                  | 说明              |
| --------------- | --------------------- | --------------- |
| `ls`            | `ls -l`               | 列出当前目录文件及详细信息   |
| `cd`            | `cd /home/pwd`        | 切换目录            |
| `pwd`           | `pwd`                 | 显示当前目录路径        |
| `mkdir`         | `mkdir test`          | 创建目录            |
| `rmdir`         | `rmdir test`          | 删除空目录           |
| `rm`            | `rm file.txt`         | 删除文件            |
| `rm -r`         | `rm -r build/`        | 递归删除目录及内容       |
| `rm -rf`        | `rm -rf build/`       | 强制递归删除目录及内容（危险） |
| `cp`            | `cp file1 file2`      | 复制文件            |
| `cp -r`         | `cp -r dir1 dir2`     | 复制目录及内容         |
| `mv`            | `mv old.txt new.txt`  | 重命名或移动文件        |
| `touch`         | `touch newfile.txt`   | 创建空文件或更新文件时间    |
| `cat`           | `cat file.txt`        | 显示文件内容          |
| `more` / `less` | `less file.txt`       | 分页显示文件内容        |
| `head`          | `head -n 10 file.txt` | 显示文件前 10 行      |
| `tail`          | `tail -n 10 file.txt` | 显示文件最后 10 行     |

---

## 2. 文件权限与所有权

| 命令      | 用法示例                    | 说明           |
| ------- | ----------------------- | ------------ |
| `chmod` | `chmod 755 file`        | 修改文件权限       |
| `chown` | `chown user:group file` | 修改文件所有者和用户组  |
| `ls -l` | `ls -l`                 | 查看文件权限、拥有者和组 |

---

## 3. 软件包管理（Ubuntu/Debian 系统）

| 命令                           | 用法示例      | 说明                              |
| ---------------------------- | --------- | ------------------------------- |
| `sudo apt update`            | 更新软件包列表   | 不安装软件，只刷新源信息                    |
| `sudo apt upgrade -y`        | 升级已安装软件   | 自动确认升级                          |
| `sudo apt install <package>` | 安装软件      | 例如 `sudo apt install g++ cmake` |
| `sudo apt remove <package>`  | 删除软件      |                                 |
| `apt list --upgradable`      | 查看可升级的软件包 |                                 |

---

## 4. 系统信息

| 命令             | 用法示例       | 说明             |
| -------------- | ---------- | -------------- |
| `uname -a`     | 查看系统信息     | 包括内核版本         |
| `df -h`        | 查看磁盘使用情况   | `-h` 以人类可读形式显示 |
| `free -h`      | 查看内存使用情况   |                |
| `top` / `htop` | 实时显示进程资源占用 |                |
| `whoami`       | 显示当前用户     |                |
| `uptime`       | 系统运行时间     |                |

---

## 5. 进程管理

| 命令 | 用法示例 | 说明 |
|------|----------|------|
| `ps` | `ps aux` | 查看当前运行的进程 |
| `top` | `top` | 动态显示系统进程 |
| `kill` | `kill <PID>` | 杀死进程 |
| `kill -9 <PID>` | 强制杀死进程 |
| `pkill` | `pkill process_name` | 按进程名杀死进程 |
| `jobs` | 查看后台任务 |
| `fg` | `fg %1` | 将后台任务调回前台 |
| `bg` | `bg %1` | 将停止的任务放到后台运行 |

---

## 6. 网络相关

| 命令 | 用法示例 | 说明 |
|------|----------|------|
| `ping` | `ping www.baidu.com` | 测试网络连通性 |
| `ifconfig` / `ip addr` | 查看网络接口信息 |
| `netstat -tuln` | 查看监听端口 |
| `ss -tuln` | 查看监听端口（新推荐命令） |
| `curl` | `curl http://example.com` | 命令行访问网页 |
| `wget` | `wget http://example.com/file` | 下载文件 |

---

## 7. 压缩与解压

| 命令 | 用法示例 | 说明 |
|------|----------|------|
| `tar -cvf archive.tar file1 file2` | 创建 tar 文件 |
| `tar -xvf archive.tar` | 解压 tar 文件 |
| `tar -czvf archive.tar.gz dir` | 压缩为 tar.gz |
| `tar -xzvf archive.tar.gz` | 解压 tar.gz |
| `zip` / `unzip` | 压缩 / 解压 zip 文件 |

---

## 8. 搜索与查找

| 命令 | 用法示例 | 说明 |
|------|----------|------|
| `find` | `find . -name "*.cpp"` | 在当前目录查找 cpp 文件 |
| `grep` | `grep "main" *.cpp` | 在文件中搜索文本 |
| `grep -r` | `grep -r "main" ./src` | 递归搜索 |
| `locate` | `locate hello.cpp` | 快速查找文件（需 `sudo updatedb`） |

---

## 9. 编辑器

| 命令 | 用法示例 | 说明 |
|------|----------|------|
| `nano file.txt` | 打开 nano 编辑器 |
| `vim file.txt` | 打开 vim 编辑器 |
| `cat file.txt` | 查看文件内容 |

---

## 10. Git 相关

| 命令 | 用法示例 | 说明 |
|------|----------|------|
| `git init` | 初始化本地仓库 |
| `git status` | 查看文件状态 |
| `git add .` | 添加所有文件到暂存区 |
| `git commit -m "message"` | 提交修改 |
| `git remote add origin <url>` | 添加远程仓库 |
| `git push -u origin master` | 推送到远程仓库 |
| `git pull` | 拉取远程最新更新 |

---

## 11. 其他常用命令

| 命令 | 用法示例 | 说明 |
|------|----------|------|
| `echo` | `echo "Hello"` | 打印内容 |
| `date` | `date` | 查看当前时间 |
| `history` | 查看历史命令 |
| `clear` | 清屏 |
| `alias ll='ls -l'` | 创建命令别名 |

