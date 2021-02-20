
$Organizational_Unit= "Advertising, Media & Brand Management"
$ResultFile_NAME = "Lista_usuarios_AdvertisingMediaBrandManagement"
$ResultFile_PATH = "Z:\Desktop\" + $ResultFile_NAME + ".csv"

Get-Aduser -filter {division -like $Organizational_Unit } -Properties * | 
Select-Object Samaccountname, name, mail, personalTitle |
Export-csv -Path $ResultFile_PATH -NoTypeInformation -Encoding UTF8