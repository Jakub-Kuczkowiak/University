
#!/usr/bin/env bash

# Java
sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update
sudo apt-get install oracle-java8-installer

# Groovy

curl -s get.sdkman.io | bash
source "$HOME/.sdkman/bin/sdkman-init.sh"
sdk install groovy

# Gradle

sudo add-apt-repository ppa:cwchien/gradle
sudo apt-get update
sudo apt-get install gradle

# Load database

psql -f database_create_script.sql

# Build Backend

gradle clean build

# Build Frontend

cd web/
npm install
bower install
gulp build