# Docker tutorial

Assume that user has all the permissions on a host.
Alternative is run under `sudo`.


## First run

```bash
docker run -d -p 80:80 docker/getting-started
```

Same, but with long options:
```bash
docker run --detach --publish 80:80 docker/getting-started
```

## Check what's running

```bash
docerk stats
```

## Stop container

```bash
docker stop --time 20 CONTAINER_NAME
```

