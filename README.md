OS Jackfruit Container Engine Project
=====================================
AUTHORS:
YASHAS - PES2UG24CS609
VARUN SAHU - PES2UG24CS576

Overview
This project implements a lightweight container engine using Linux system programming concepts such as process isolation, namespaces, and kernel modules. It demonstrates multi‑container execution, process monitoring, workload scheduling, kernel‑level monitoring, and system cleanup.

Task 1 – Multi‑container Supervision
Two independent containers (alpha and beta) are created using separate root filesystems. Each runs its own isolated shell environment.

Commands:
cd ~/OS-Jackfruit
sudo ./engine start alpha ./rootfs /bin/sh
sudo ./engine start beta ./rootfs-beta /bin/sh
+------------------+       +------------------+
|   Container A    |       |   Container B    |
| Rootfs: ./rootfs |       | Rootfs: ./rootfs-beta |
| Process: /bin/sh |       | Process: /bin/sh |
+------------------+       +------------------+
-----------------------------------------------------------------------------------------------------------------------
Task 2 – Metadata Tracking (engine ps)
The engine provides a process listing feature to display active containers and their execution details.

Commands:
sudo ./engine ps

+-----------+--------+----------+
| Container |   PID  |  State   |
+-----------+--------+----------+
| alpha     |  3934  | running  |
| beta      |  3964  | running  |
+-----------+--------+----------+
-----------------------------------------------------------------------------------------------------------------------
Task 3 – Concurrent Workloads
Two containers simulate different workloads:
• CPU‑bound workload (continuous output)
• IO‑bound workload (delayed output)

Commands:
# CPU workload
sudo ./engine start alpha ./rootfs /bin/sh
for i in $(seq 1 50); do echo cpu; done

# IO workload
sudo ./engine start beta ./rootfs-beta /bin/sh
for i in $(seq 1 20); do echo io; sleep 1; done
-----------------------------------------------------------------------------------------------------------------------

Task 4 – Kernel Memory Monitor
A custom kernel module monitors system activity and demonstrates kernel‑level interaction.

Commands:
sudo insmod monitor.ko
sudo dmesg | tail
-----------------------------------------------------------------------------------------------------------------------

Task 5 – Scheduler Experiment
Demonstrates Linux scheduling with CPU‑intensive and IO‑bound tasks.

Commands
sudo ./engine start cpu ./rootfs /bin/sh
for i in $(seq 1 100000000); do :; done

sudo ./engine start io ./rootfs-beta /bin/sh
for i in $(seq 1 20); do echo io; sleep 1; done
-----------------------------------------------------------------------------------------------------------------------

Logging
Each container redirects its output to a dedicated log file.
Command:
sudo ./engine logs alpha
-----------------------------------------------------------------------------------------------------------------------

Soft and Hard Limits
Demonstrates resource constraints using cgroups.
commands:
sudo ./engine run gamma ./rootfs-gamma ./memory_hog
sudo dmesg | grep container
-----------------------------------------------------------------------------------------------------------------------
Task 6 – Cleanup
Safely terminate all running containers and kernel modules.
Commands:
sudo pkill engine
ps aux | grep engine
sudo rmmod monitor
lsmod | grep monitor
-----------------------------------------------------------------------------------------------------------------------
conclusion:
This project successfully demonstrates container creation with process isolation,
multi-container execution, process supervision, concurrent workload handling, kernel-level 
monitoring, scheduling behaviour, and proper cleanup of resources
