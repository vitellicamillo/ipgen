 
 $users = @()
 $result = @()
 $group = "GRP_PROXY_PERFIL_5"
 $path = "Z:\Desktop\Netskope\usuarios_"+ $group +".csv"
  
 $users = Get-ADGroupMember -identity $group |select-object samaccountname 
 
 foreach ($user in $users){
 $result += Get-Aduser -identity $user.samaccountname -Properties * | Select-Object SamAccountName, Name, ExtensionAttribute14, Division, ExtensionAttribute1
 }

 $result | Export-csv -Path $path -NoTypeInformation -Encoding utf8





