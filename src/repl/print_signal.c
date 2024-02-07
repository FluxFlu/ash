void printSignal(int sig) {
	switch (sig) {
		case SIGILL:
			printLit("Illegal instruction");
			break;
		case SIGSEGV:
			printLit("Segmentation fault");
			break;
		case SIGTERM:
			printLit("Terminated");
			break;
		case SIGQUIT:
			printLit("Quit");
			break;
		case SIGKILL:
			printLit("Killed");
			break;
		case SIGHUP:
			printLit("Hangup");
			break;
		case SIGUSR1:
			printLit("User defined signal 1");
			break;
		case SIGUSR2:
			printLit("User defined signal 2");
			break;
		case SIGINT:
			printLit("Interrupt");
			break;
		case SIGPIPE:
			printLit("Broken pipe");
			break;
		default:
            char buf[4];
            snprintf(buf, 4, "%i", sig);
			printLit("Killed by unhandled signal ");
            print(buf, 4);
			break;
	}
}