import pandas as pd

# Read the CSV file
df = pd.read_csv('./dataSets/cropProductionDataset.csv')

# Manually encode categorical columns by mapping them to unique numerical values
categorical_columns = ['State', 'District', 'Crop', 'Season', 'Area Units', 'Production Units']

# Create a dictionary to store mappings for each column
mappings = {}

for column in categorical_columns:
    # Get unique values in the column and map them to integers
    unique_values = df[column].unique()
    mappings[column] = {value: idx for idx, value in enumerate(unique_values)}
    
    # Replace the categorical values with their corresponding numerical values
    df[column] = df[column].map(mappings[column])

# The dataframe now has numerical values for all columns
print(df.head())

# Write the new data to a CSV file
df.to_csv('output_data.csv', index=False)

# Optional: print mappings to understand the encoding
for column, mapping in mappings.items():
    print(f"Mapping for {column}: {mapping}")
