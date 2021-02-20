
Get-Aduser -filter {division -like "Advertising, Media & Brand Management"} -Properties * | 
Select-Object Samaccountname, name, mail, personalTitle |
Export-csv -Path Z:\Desktop\Lista_usuarios_AdvertisingMediaBrandManagement.csv -NoTypeInformation -Encoding UTF8
