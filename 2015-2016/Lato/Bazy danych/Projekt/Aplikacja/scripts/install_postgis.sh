#!/bin/bash

# This script:
#   * installs PostgreSQL with PostGIS
#   * creates PostGIS database template
#   * creates new database user
#   * creates new database

POSTGRES_DB=${1:-"vagrant"}
POSTGRES_USER=${2:-"vagrant"}
POSTGRES_PASS=${3:-"vagrant"}

export DEBIAN_FRONTEND=noninteractive

if [ -f /etc/os-release ]; then
    # Get OS name
    OS=`cat /etc/os-release | sed -ne 's|^ID=\([[:alnum:]]*\)|\1|p'`

    if [ "$OS" == "ubuntu" ]; then
        # Assuming Ubuntu 14.04
        POSTGRES_VERSION="9.3"
        POSTGIS_VERSION="2.1"
    else
        # Assuming Debian 8 (Jessie)
        POSTGRES_VERSION="9.4"
        POSTGIS_VERSION="2.1"
    fi
fi

# Update packages list
apt-get update

# Install PostgreSQL with PostGIS
apt-get install -y postgresql-${POSTGRES_VERSION} \
                   postgresql-contrib-${POSTGRES_VERSION} \
                   postgis-${POSTGIS_VERSION} \
                   postgresql-${POSTGRES_VERSION}-postgis-${POSTGIS_VERSION}

# Install PostgreSQL development package
apt-get install -y postgresql-server-dev-${POSTGRES_VERSION}

# Create PostGIS database template
POSTGIS_SQL_PATH=/usr/share/postgresql/${POSTGRES_VERSION}/contrib/postgis-${POSTGIS_VERSION}
sudo -u postgres createdb -E UTF8 template_postgis
sudo -u postgres psql -d postgres -c "UPDATE pg_database SET datistemplate='true' WHERE datname='template_postgis';"
sudo -u postgres psql -d template_postgis -f ${POSTGIS_SQL_PATH}/postgis.sql
sudo -u postgres psql -d template_postgis -f ${POSTGIS_SQL_PATH}/spatial_ref_sys.sql
sudo -u postgres psql -d template_postgis -f ${POSTGIS_SQL_PATH}/postgis_comments.sql
sudo -u postgres psql -d template_postgis -c "GRANT ALL ON geometry_columns TO PUBLIC;"
sudo -u postgres psql -d template_postgis -c "GRANT ALL ON spatial_ref_sys TO PUBLIC;"
sudo -u postgres psql -d template_postgis -c "GRANT ALL ON geography_columns TO PUBLIC;"

# Create database user
sudo -u postgres psql postgres -c "CREATE USER ${POSTGRES_USER} WITH SUPERUSER PASSWORD '${POSTGRES_PASS}';"

# Create database
sudo -u postgres createdb -T template_postgis --owner=${POSTGRES_USER} ${POSTGRES_DB}

{ echo; echo "host all all 0.0.0.0/0 md5"; } >> /etc/postgresql/${POSTGRES_VERSION}/main/pg_hba.conf

# Uncomment default setting and set listening on all ports
POSTGRESQL_CONF="/etc/postgresql/9.3/main/postgresql.conf"
sed -i "/listen_addresses = 'localhost'/s/^#//g" ${POSTGRESQL_CONF}
sed -i "/listen_addresses = 'localhost'/s/localhost/*/g" ${POSTGRESQL_CONF}

# Restart PostgreSQL server
service postgresql restart

