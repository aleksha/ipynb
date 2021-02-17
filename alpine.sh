apk --update add \
bash \
curl \
wget \
ca-certificates \
libstdc++ \
glib \
&& wget -q -O /etc/apk/keys/sgerrand.rsa.pub https://raw.githubusercontent.com/sgerrand/alpine-pkg-node-bower/master/sgerrand.rsa.pub \
&& curl -L "https://github.com/sgerrand/alpine-pkg-glibc/releases/download/2.23-r3/glibc-2.23-r3.apk" -o glibc.apk \
&& apk add glibc.apk \
&& curl -L "https://github.com/sgerrand/alpine-pkg-glibc/releases/download/2.23-r3/glibc-bin-2.23-r3.apk" -o glibc-bin.apk \
&& apk add glibc-bin.apk \
&& curl -L "https://github.com/andyshinn/alpine-pkg-glibc/releases/download/2.25-r0/glibc-i18n-2.25-r0.apk" -o glibc-i18n.apk \
&& apk add --allow-untrusted glibc-i18n.apk \
&& /usr/glibc-compat/bin/localedef -i en_US -f UTF-8 en_US.UTF-8 \
&& /usr/glibc-compat/sbin/ldconfig /lib /usr/glibc/usr/lib \
&& rm -rf glibc*apk /var/cache/apk/*
