# Now you need to create a user and database for the user. 
# This needs to be run from a postgres user account on your system.

sudo -u postgres psql -c "CREATE USER $1 WITH PASSWORD '$2';"

