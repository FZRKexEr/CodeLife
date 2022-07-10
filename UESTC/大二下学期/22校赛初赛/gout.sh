limit=1
while([[ -f "./test/"$limit".in" ]]) do
  echo "正在生成第"$limit"组数据的答案。"
  (cat "./test/"$limit".in" | ./a.out) > "./test/"$limit".out"
  let "limit++"
done
