static void
focusmaster(const Arg *arg) {
	focus(nexttiled(selmon->clients));
}
