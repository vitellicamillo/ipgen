$s = New-PSSession -HostName 3.82.44.56 -UserName administrator
 
Invoke-Command -ScriptBlock {
    Import-module -PSSession $s -Name ActiveDirectory
    $result = @()
    $result = Get-aduser -filter * -properties * | select-object SamAccountName
    $result | Export-csv ~/Desktop/test.csv -NoTypeInformation -Encoding utf8
}