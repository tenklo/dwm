static void
focusurgent(const Arg *arg) {
	Client *c;
	int i;
	/* for (m = mons; m && m->num != r->monitor; m = m->next); */
	for(c=selmon->clients; c && !c->isurgent; c=c->next);
	/* for(c=mons->clients; c && !c->isurgent; c=c->next); */
	if(c) {
		for(i=0; i < LENGTH(tags) && !((1 << i) & c->tags); i++);
		if(i < LENGTH(tags)) {
            /* selmon = c->mon; */
			const Arg a = {.ui = 1 << i};
			view(&a);
			focus(c);
		}
	}
}
