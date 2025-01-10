
# Installation and initialization of the postgresql server

sudo dnf install postgresql-server postgresql-contrib

# The postgresql server is not running and disabled by default. To set it to start at boot, run:

sudo systemctl enable postgresql

# The database needs to be populated with initial data after installation

sudo postgresql-setup --initdb --unit postgresql

# To start the postgresql server manually, run

sudo systemctl start postgresql

