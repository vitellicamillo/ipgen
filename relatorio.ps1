$ResultFile = @()
$SourceFile_PATH = "Z:\Desktop\Lista-2.txt"
$ResultFile_PATH = "Z:\Desktop\Result-4.csv"
$SourceFile = Get-Content -Path $SourceFile_PATH

foreach ($Name in $SourceFile){

    $Result += get-aduser -filter{name -like $Name} -properties * | 
    select-object SamAccountName, name, mail, ExtensionAttribute14, Division, ExtensionAttribute1
} 

$ResultFile | Export-csv -Path $ResultFile_PATH -NoTypeInformation -Encoding UTF8
