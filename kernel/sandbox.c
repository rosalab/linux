#include <linux/fdtable.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/rcupdate.h>
#include <linux/sched/signal.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(sandbox){
	// Handle files
	// TODO: handle files with more intelligence.
	struct files_struct *files = current->files;

	spin_lock(&files->file_lock);
	struct fdtable *fdt = files_fdtable(files);

	for (unsigned int i = 0; i < fdt->max_fds; i++) {
		struct file *file = fdt->fd[i];
		if (!file) continue;

		// Skipping stdio
		if (i <= 2) continue;

		// close only if regular file
		if (S_ISREG(file_inode(file)->i_mode)) {
			get_file(file);
			file_close_fd_locked(files, i);
			fput(file);
		}
	}

	spin_unlock(&files->file_lock);

	return 0;
}

