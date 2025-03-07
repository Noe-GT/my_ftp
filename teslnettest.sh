for i in $(seq 1 100);
do
    telnet 127.0.0.1 4242 &
done