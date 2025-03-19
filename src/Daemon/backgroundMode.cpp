// #include <iostream>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <csignal>
// #include "../headers/Daemon.h"

// void Daemon::backgroundMode() {
//     pid_t pid = fork();
//     if (pid < 0) {
//         exit(EXIT_FAILURE);
//     }

//     // End of parenting process
//     if (pid > 0) {
//         exit(EXIT_SUCCESS);
//     }

//     // Create a new session
//     setsid();

//     // Ignore terminal close signal
//     signal(SIGHUP, SIG_IGN);

//     pid = fork();
//     if (pid < 0) {
//         exit(EXIT_FAILURE);
//     }
//     if (pid > 0) {
//         exit(EXIT_SUCCESS);
//     }
//     umask(0);

//     // Close standard threads
//     close(STDIN_FILENO);
//     close(STDOUT_FILENO);
//     close(STDERR_FILENO);

//     // log function here
//     // TODO
//     int logFile = open("/var/log/sensor_daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
//     if (logFile == -1) {
//         exit(EXIT_FAILURE);
//     }

//     // Перенаправлення стандартного виводу в файл
//     dup2(logFile, STDOUT_FILENO);
//     dup2(logFile, STDERR_FILENO);

// }