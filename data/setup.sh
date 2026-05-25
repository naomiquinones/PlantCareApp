#!/bin/bash
# PlantCareApp Database Setup Script
# Run this once to initialize the database

DB_PATH="data/plants.db"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "Setting up PlantCareApp database..."

# Create database and schema
echo "Creating schema..."
sqlite3 "$SCRIPT_DIR/plants.db" < "$SCRIPT_DIR/schema.sql"

# Import plant types and factors from JSON
echo "Importing plant types..."
python3 "$SCRIPT_DIR/import_plant_types.py"

echo "Importing factors..."
python3 "$SCRIPT_DIR/import_factors.py"

echo "Setup complete. Database created at $SCRIPT_DIR/plants.db"