
SUBDIRS= src/*/ 



all clean:
	#@echo Copy external library
	#@cp $(LISTLIB) $(LIBEXTDIR) 
	for d in $(SUBDIRS) ; do ( cd $$d ; $(MAKE) $@ ) ; done

eclean: clean
	-find . -name '*~' -print0 | xargs -0 rm
