import pandas as pd

# Read the original CSV file
df = pd.read_csv('./dataSets/output_data.csv')

# Remove the last three columns
df_modified = df.iloc[:, :-3]

# Save the modified DataFrame to a new CSV file
df_modified.to_csv('./dataSets/input.csv', index=False)

print("The last three columns have been removed and the new file is saved as 'output_data.csv'.")
