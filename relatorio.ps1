$Result = @()
$ListaNome = Get-Content -Path 'Z:\Desktop\Lista-2.txt'

foreach ($Nome in $ListaNome){

    $Result += get-aduser -filter{name -like $Nome} -properties * | 
    select-object SamAccountName, name, mail, ExtensionAttribute14, Division, ExtensionAttribute1
} 

$Result | Export-csv -Path Z:\Desktop\Result-4.csv -NoTypeInformation -Encoding UTF8
