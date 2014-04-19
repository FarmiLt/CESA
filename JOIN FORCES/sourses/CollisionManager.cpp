//////////////////////////////////////////////////////
//
//	詳細		：衝突管理クラスメソッド
//	作成者		：岸　将史
//	最終更新日	：2014/04/16
//
//////////////////////////////////////////////////////
#include "CollisionManager.h"
#include "Camera.h"


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：リスト内の全要素を削除する
第１引数	：－
返却値		：－

*************************************************************************/
C_CollisionManager::~C_CollisionManager(){
	m_pCubeList.clear();
	m_pSphereList.clear();
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：リスト内に登録されているエンティティの衝突判定を行う
第１引数	：－
返却値		：－

*************************************************************************/
void C_CollisionManager::Update(){
	// 操作対象がいないならば衝突判定を行わない
	if (m_pController == nullptr) return;

	std::list<C_Game3DEntity*>::iterator iterSphere = m_pSphereList.begin();
	std::list<C_Game3DEntity*>::iterator iterCube = m_pCubeList.begin();

	if (m_pController->IsType() == eENTITY::ENTITY_SPHERE){
		// プレイヤーの衝突フラグ
		bool crashed = false;

		while (iterSphere != m_pSphereList.end()){
			// すでに衝突している場合は判定対象にしない
				// なぜなら連続で操作対象が切り換ってしまうため
			
				// 衝突判定（球と球）
			if (Crash_Sphere2Sphere(m_pController, (*iterSphere))){
				crashed = true;

				// すでにぶつかっている場合操作対象変更処理を行わない
				if (!(*iterSphere)->IsCrashing()){
					// お互いを衝突中にする
					m_pController->Crashed(crashed);
					(*iterSphere)->Crashed(crashed);

					// 操作対象交代
					m_pController->ChangeControl();
					(*iterSphere)->ChangeControl();

					// リスト内を変更する
					m_pSphereList.push_back(m_pController);
					m_pController = (*iterSphere);
					// リストから削除(この時点でイテレータが役に立たなくなる、でも問題ない)
					m_pSphereList.erase(iterSphere);

					// カメラの対象を切り換える
					C_BaseCamera::GetInstance()->SetOwner(m_pController);

					// 当たったらループを抜ける
					return;
				}
			}
			else{
				(*iterSphere)->Crashed(false);
			}
			++iterSphere;
		}
		m_pController->Crashed(crashed);
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/16
用途		：エンティティをリストに登録する
第１引数	：エンティティ
返却値		：－

*************************************************************************/
void C_CollisionManager::RegisterEntity(C_Game3DEntity* object){
	// もし、操作対象ならばリスト外に保持
	if (object->IsControlling()){
		m_pController = object;
	}
	else{
		// オブジェクト毎でリスト管理する
		switch(object->IsType()){
			// 立方体
		case eENTITY::ENTITY_CUBE :
			m_pCubeList.push_back(object);
			break;

			// 球体
		case eENTITY::ENTITY_SPHERE :
			m_pSphereList.push_back(object);
			break;

			// TODO: 図形を追加するならここに

		default:
			MessageBox(NULL, TEXT("そのオブジェクトのリストが存在しません"), TEXT("ERROR"), MB_OK);
			break;
		}
	}
}


/*************************************************************************

作成者		：岸　将史
最終更新日	：2014/04/18
用途		：球と球の衝突判定
第１引数	：操作対象
第２引数	：球体
返却値		：衝突している→true, 衝突していない→false

*************************************************************************/
bool C_CollisionManager::Crash_Sphere2Sphere(C_Game3DEntity* pController, C_Game3DEntity* pSphere){
	// ２つのエンティティの距離を出す
	DirectX::SimpleMath::Vector3 vec = pSphere->GetPosition() - pController->GetPosition();
	float distance = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		/*vec.Distance*/;

	// ２点間の距離がお互いの半径を足した値より小さければ当たっている
	if (distance <= ( pSphere->GetRadius() + pController->GetRadius() ) ){
		return true;
	}

	return false;
}