cd ~/17373452-lab
make clean
make
/OSLAB/gxemul -E testmips -C R3000 -M 64 ~/17373452-lab/gxemul/vmlinux
