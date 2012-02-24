## topic_autostart

Now that I have been working with Tictocs for a while, I am finding it prone to mistakes
because I have to rememeber to

* begin
* listen
* add to updater (if needed)

Would be nice if this could be done in a single operation

### Alternatives

1. begin() takes optional listen and updater parameters 
2. Connectable has a virtual begin, then you call the connector once, and it loops
through all the connectable objects and begins them.  Sadly it does not KNOW about
the connectable objects yet though because they have not listen()ed to anything.
